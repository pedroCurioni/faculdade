package view;

import controllers.AcomodacaoController;
import controllers.MainController;
import dto.AcomodacaoDto;
import dto.TipoAcomodacaoDto;
import enums.EEstadoOcupacao;
import exception.AcomodacaoException;
import exception.TipoAcomodacaoException;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Set;

public class AcomodacaoView extends JFrame {

    private static final long serialVersionUID = -1091761697182973886L;
    private final AcomodacaoController acomodacaoController = MainController.getAcomodacaoController();

    private JTextField numeroField;
    private JTextField ocupacaoMaxField;
    private JComboBox<String> tipoComboBox;
    private JList<String> acomodacaoList;
    private JTextField searchNumeroField;
    private JTextArea acomodacaoDetailsArea;
    private JTextField numeroField2;
    private JComboBox<EEstadoOcupacao> estadoComboBox;

    public AcomodacaoView() {
        setTitle("Acomodação");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JTabbedPane tabbedPane = new JTabbedPane();

        tabbedPane.addTab("Criar", createCreatePanel());
        tabbedPane.addTab("Listar Acomodações", createListPanel());
        tabbedPane.addTab("Buscar acomodação", createSearchPanel());
        tabbedPane.addTab("Alterar Estado", createAlterarEstadoPanel());

        add(tabbedPane);
    }

    private JPanel createCreatePanel() {
        JPanel createPanel = new JPanel(new GridLayout(5, 2));
        createPanel.add(new JLabel("Numero (numérico):"));
        numeroField = new JTextField();
        createPanel.add(numeroField);

        createPanel.add(new JLabel("Ocupacao Max (numérico):"));
        ocupacaoMaxField = new JTextField();
        createPanel.add(ocupacaoMaxField);

        createPanel.add(new JLabel("Tipo:"));
        tipoComboBox = new JComboBox<>(acomodacaoController.getTiposAcomodacao().toArray(new String[0]));
        createPanel.add(tipoComboBox);

        JButton createButton = new JButton("Criar Acomodação");
        createPanel.add(createButton);

        createButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                createAcomodacao();
            }
        });

        return createPanel;
    }

    private JPanel createListPanel() {
        JPanel viewPanel = new JPanel(new BorderLayout());
        acomodacaoList = new JList<>();
        viewPanel.add(new JScrollPane(acomodacaoList), BorderLayout.CENTER);

        JButton refreshButton = new JButton("Atualizar Lista");
        viewPanel.add(refreshButton, BorderLayout.SOUTH);

        refreshButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                refreshAcomodacaoList();
            }
        });

        return viewPanel;
    }

    private JPanel createSearchPanel() {
        JPanel searchPanel = new JPanel(new BorderLayout());
        JPanel inputPanel = new JPanel(new GridLayout(2, 2));
        inputPanel.add(new JLabel("Numero (numérico):"));
        searchNumeroField = new JTextField();
        inputPanel.add(searchNumeroField);

        JButton searchButton = new JButton("Buscar Acomodação");
        inputPanel.add(searchButton);

        searchPanel.add(inputPanel, BorderLayout.NORTH);

        acomodacaoDetailsArea = new JTextArea();
        acomodacaoDetailsArea.setEditable(false);
        searchPanel.add(new JScrollPane(acomodacaoDetailsArea), BorderLayout.CENTER);

        searchButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                searchAcomodacao();
            }
        });

        return searchPanel;
    }

    private JPanel createAlterarEstadoPanel() {
        JPanel alterarEstadoPanel = new JPanel(new GridLayout(3, 2));
        alterarEstadoPanel.add(new JLabel("Numero (numérico):"));
        numeroField2 = new JTextField();
        alterarEstadoPanel.add(numeroField2);

        alterarEstadoPanel.add(new JLabel("Novo Estado:"));
        estadoComboBox = new JComboBox<>(EEstadoOcupacao.values());
        alterarEstadoPanel.add(estadoComboBox);

        JButton alterarButton = new JButton("Alterar Estado");
        alterarEstadoPanel.add(alterarButton);

        alterarButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                alterarEstadoAcomodacao();
            }
        });

        return alterarEstadoPanel;
    }

    private void createAcomodacao() {
        try {
            int numero = Integer.parseInt(numeroField.getText());
            int ocupacaoMax = Integer.parseInt(ocupacaoMaxField.getText());
            String tipo = (String) tipoComboBox.getSelectedItem();
            TipoAcomodacaoDto tipoAcomodacaoDto = acomodacaoController.getTipoAcomodacao(tipo);
            AcomodacaoDto acomodacaoDto = new AcomodacaoDto(numero, ocupacaoMax, EEstadoOcupacao.DISPONIVEL, tipoAcomodacaoDto);
            acomodacaoController.createAcomodacao(acomodacaoDto);
            MainController.save();
            JOptionPane.showMessageDialog(null, "Acomodação criada com sucesso!");
        } catch (AcomodacaoException | TipoAcomodacaoException ex) {
            JOptionPane.showMessageDialog(null, "Error: " + ex.getMessage());
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(null, "Formato invalido, campos de número deve conter apenas números", "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void refreshAcomodacaoList() {
        Set<Integer> acomodacoes = acomodacaoController.getAcomodacoes();
        acomodacaoList.setListData(acomodacoes.stream().map(String::valueOf).toArray(String[]::new));
    }

    private void searchAcomodacao() {
        try {
            int numero = Integer.parseInt(searchNumeroField.getText());
            AcomodacaoDto acomodacaoDto = acomodacaoController.getAcomodacaoDto(numero);
            acomodacaoDetailsArea.setText(acomodacaoDto.toString());
        } catch (AcomodacaoException | TipoAcomodacaoException ex) {
            acomodacaoDetailsArea.setText("Error: " + ex.getMessage());
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(null, "Formato invalido, campos de número deve conter apenas números", "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void alterarEstadoAcomodacao() {
        try {
            int numero = Integer.parseInt(numeroField2.getText());
            EEstadoOcupacao novoEstado = (EEstadoOcupacao) estadoComboBox.getSelectedItem();
            acomodacaoController.alterarEstadoAcomodacao(numero, novoEstado);
            MainController.save();
            JOptionPane.showMessageDialog(null, "Estado da acomodação alterado com sucesso!");
        } catch (AcomodacaoException | TipoAcomodacaoException ex) {
            JOptionPane.showMessageDialog(null, "Error: " + ex.getMessage());
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(null, "Formato invalido, campos de número deve conter apenas números", "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }
}