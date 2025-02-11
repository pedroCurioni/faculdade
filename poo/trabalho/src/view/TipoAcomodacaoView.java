package view;

import controllers.AcomodacaoController;
import controllers.MainController;
import dto.TipoAcomodacaoDto;
import exception.TipoAcomodacaoException;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Set;

public class TipoAcomodacaoView extends JFrame {

    private static final long serialVersionUID = -2693858877868878507L;
    private final AcomodacaoController acomodacaoController = MainController.getAcomodacaoController();

    private JTextField nomeField;
    private JTextField tarifaDiariaField;
    private JTextField adicionalAcompanhanteField;
    private JTextField searchNomeField;
    private JTextArea tipoAcomodacaoDetailsArea;
    private JList<String> tipoAcomodacaoList;

    public TipoAcomodacaoView() {
        setTitle("Tipo Acomodacao");
        setSize(500, 400);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP);
        tabbedPane.addTab("Criar Tipo de Acomodação", createCreatePanel());
        tabbedPane.addTab("Listar Tipo de Acomodações", createViewPanel());
        tabbedPane.addTab("Buscar Tipo de Acomodações", createSearchPanel());

        add(tabbedPane);
    }

    private JPanel createCreatePanel() {
        JPanel createPanel = new JPanel(new GridLayout(4, 2));

        createPanel.add(new JLabel("Nome:"));
        nomeField = new JTextField();
        createPanel.add(nomeField);

        createPanel.add(new JLabel("Tarifa Diaria (numérico):"));
        tarifaDiariaField = new JTextField();
        createPanel.add(tarifaDiariaField);

        createPanel.add(new JLabel("Adicional Acompanhante (numérico):"));
        adicionalAcompanhanteField = new JTextField();
        createPanel.add(adicionalAcompanhanteField);

        JButton createButton = new JButton("Criar");
        createPanel.add(createButton);

        createButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                handleCreateButton();
            }
        });

        return createPanel;
    }

    private void handleCreateButton() {
        try {
            acomodacaoController.createTipoAcomodacao(
                    new TipoAcomodacaoDto(
                            nomeField.getText(),
                            Double.parseDouble(tarifaDiariaField.getText()),
                            Double.parseDouble(adicionalAcompanhanteField.getText())
                    )
            );
            MainController.save();
            JOptionPane.showMessageDialog(null, "Tipo Acomodacao created successfully!");
        } catch (TipoAcomodacaoException ex) {
            JOptionPane.showMessageDialog(null, "Error: " + ex.getMessage());
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(null, "Formato invalido, campos de número deve conter apenas números", "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }

    private JPanel createViewPanel() {
        JPanel viewPanel = new JPanel(new BorderLayout());

        tipoAcomodacaoList = new JList<>();
        viewPanel.add(new JScrollPane(tipoAcomodacaoList), BorderLayout.CENTER);

        JButton refreshButton = new JButton("Refresh");
        viewPanel.add(refreshButton, BorderLayout.SOUTH);

        refreshButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                handleRefreshButton();
            }
        });

        return viewPanel;
    }

    private void handleRefreshButton() {
        Set<String> tiposAcomodacao = acomodacaoController.getTiposAcomodacao();
        tipoAcomodacaoList.setListData(tiposAcomodacao.toArray(new String[0]));
    }

    private JPanel createSearchPanel() {
        JPanel searchPanel = new JPanel(new BorderLayout());

        JPanel inputPanel = new JPanel(new GridLayout(2, 2));
        inputPanel.add(new JLabel("Nome:"));
        searchNomeField = new JTextField();
        inputPanel.add(searchNomeField);

        JButton searchButton = new JButton("Search");
        inputPanel.add(searchButton);

        searchPanel.add(inputPanel, BorderLayout.NORTH);

        tipoAcomodacaoDetailsArea = new JTextArea();
        tipoAcomodacaoDetailsArea.setEditable(false);
        searchPanel.add(new JScrollPane(tipoAcomodacaoDetailsArea), BorderLayout.CENTER);

        searchButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                handleSearchButton();
            }
        });

        return searchPanel;
    }

    private void handleSearchButton() {
        try {
            String nome = searchNomeField.getText();
            TipoAcomodacaoDto tipoAcomodacaoDto = acomodacaoController.getTipoAcomodacao(nome);
            tipoAcomodacaoDetailsArea.setText(tipoAcomodacaoDto.toString());
        } catch (TipoAcomodacaoException ex) {
            tipoAcomodacaoDetailsArea.setText("Error: " + ex.getMessage());
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }
}