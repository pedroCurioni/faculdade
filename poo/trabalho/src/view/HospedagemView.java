package view;

import controllers.AcomodacaoController;
import controllers.HospedagemController;
import controllers.HospedeController;
import controllers.MainController;
import dto.AcomodacaoDto;
import dto.HospedagemDto;
import dto.HospedeDto;
import dto.PagamentoDto;
import enums.EEstadoOcupacao;
import enums.ETipoPagamento;
import exception.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Date;
import java.util.Set;

public class HospedagemView extends JFrame {

    private static final long serialVersionUID = 9118575804341696L;
    private final HospedagemController hospedagemController = MainController.getHospedagemController();
    private final HospedeController hospedeController = MainController.getHospedeController();
    private final AcomodacaoController acomodacaoController = MainController.getAcomodacaoController();

    private JTextField txtHospede;
    private JTextField txtAcomodacao;
    private JTextArea hospedagemTextArea;
    private JTextField searchIdField;
    private JTextArea hospedagemDetailsArea;
    private JTextField txtHospedagemIdAddHospede;
    private JTextField txtHospedeAdd;
    private JTextField txtHospedagemIdCheckout;
    private JTextField txtFinalPayment;
    private JComboBox<ETipoPagamento> cbTipoPagamento;

    public HospedagemView() {
        setTitle("Hospedagem");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JTabbedPane tabbedPane = new JTabbedPane();
        tabbedPane.addTab("Check-IN", createCheckInPanel());
        tabbedPane.addTab("View Hospedagens", createListPanel());
        tabbedPane.addTab("Buscar Hospedagem", createSearchPanel());
        tabbedPane.addTab("Adicionar Hospede", createAddHospedePanel());
        tabbedPane.addTab("Checkout", createCheckoutPanel());

        add(tabbedPane);
    }

    private JPanel createCheckInPanel() {
        JPanel createPanel = new JPanel(new GridLayout(3, 2, 10, 10));
        createPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        createPanel.add(new JLabel("CPF do Hospede:"));
        txtHospede = new JTextField();
        createPanel.add(txtHospede);

        createPanel.add(new JLabel("Acomodacao (numérico):"));
        txtAcomodacao = new JTextField();
        createPanel.add(txtAcomodacao);

        JButton btnAddHospedagem = new JButton("Check-IN");
        createPanel.add(btnAddHospedagem);

        btnAddHospedagem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                checkIn();
            }
        });

        return createPanel;
    }

    private JPanel createListPanel() {
        JPanel viewPanel = new JPanel(new BorderLayout());
        hospedagemTextArea = new JTextArea();
        hospedagemTextArea.setEditable(false);
        viewPanel.add(new JScrollPane(hospedagemTextArea), BorderLayout.CENTER);

        JButton refreshButton = new JButton("Refresh");
        viewPanel.add(refreshButton, BorderLayout.SOUTH);

        refreshButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                listHospedagens();
            }
        });

        return viewPanel;
    }

    private JPanel createSearchPanel() {
        JPanel searchPanel = new JPanel(new BorderLayout());

        JPanel inputPanel = new JPanel(new GridLayout(2, 2));
        inputPanel.add(new JLabel("ID Hospedagem:"));
        searchIdField = new JTextField();
        inputPanel.add(searchIdField);

        JButton searchButton = new JButton("Buscar hospedagem");
        inputPanel.add(searchButton);

        searchPanel.add(inputPanel, BorderLayout.NORTH);

        hospedagemDetailsArea = new JTextArea();
        hospedagemDetailsArea.setEditable(false);
        searchPanel.add(new JScrollPane(hospedagemDetailsArea), BorderLayout.CENTER);

        searchButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                searchHospedagem();
            }
        });

        return searchPanel;
    }

    private JPanel createAddHospedePanel() {
        JPanel addHospedePanel = new JPanel(new GridLayout(3, 2, 10, 10));
        addHospedePanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        JLabel lblHospedagemIdAddHospede = new JLabel("ID Hospedagem:");
        txtHospedagemIdAddHospede = new JTextField();
        JLabel lblHospedeAdd = new JLabel("CPF dos Hospedes (Separado pro ','):");
        txtHospedeAdd = new JTextField();
        JButton btnAddHospede = new JButton("Adicionar Hospede");

        btnAddHospede.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                addHospede();
            }
        });

        addHospedePanel.add(lblHospedagemIdAddHospede);
        addHospedePanel.add(txtHospedagemIdAddHospede);
        addHospedePanel.add(lblHospedeAdd);
        addHospedePanel.add(txtHospedeAdd);
        addHospedePanel.add(new JLabel());
        addHospedePanel.add(btnAddHospede);

        return addHospedePanel;
    }

    private JPanel createCheckoutPanel() {
        JPanel checkoutPanel = new JPanel(new GridLayout(5, 2, 10, 10));
        checkoutPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        JLabel lblHospedagemIdCheckout = new JLabel("ID Hospedagem:");
        txtHospedagemIdCheckout = new JTextField();
        JLabel lblFinalPayment = new JLabel("Pagamento Final (Numero):");
        txtFinalPayment = new JTextField();
        JLabel lblTipoPagamento = new JLabel("Tipo de Pagamento:");
        cbTipoPagamento = new JComboBox<>(ETipoPagamento.values());
        JButton btnCheckout = new JButton("Checkout");

        btnCheckout.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                confirmAndCheckout();
            }
        });

        checkoutPanel.add(lblHospedagemIdCheckout);
        checkoutPanel.add(txtHospedagemIdCheckout);
        checkoutPanel.add(lblFinalPayment);
        checkoutPanel.add(txtFinalPayment);
        checkoutPanel.add(lblTipoPagamento);
        checkoutPanel.add(cbTipoPagamento);
        checkoutPanel.add(new JLabel());
        checkoutPanel.add(btnCheckout);

        return checkoutPanel;
    }

    private void checkIn() {
        try {
            HospedeDto hospede = hospedeController.getHospedeDto(txtHospede.getText());
            AcomodacaoDto acomodacao = acomodacaoController.getAcomodacaoDto(Integer.parseInt(txtAcomodacao.getText()));
            HospedagemDto hospedagemDto = new HospedagemDto(null, new Date(), hospede, new ArrayList<>(), acomodacao, null, new ArrayList<>(), null);
            String id = hospedagemController.createHospedagem(hospedagemDto);
            acomodacaoController.alterarEstadoAcomodacao(acomodacao.getNumero(), EEstadoOcupacao.OCUPADO);
            JOptionPane.showMessageDialog(null, "Hospedagem criada com sucesso! ID: " + id);
        } catch (HospedagemException | HospedeException | AcomodacaoException | TipoAcomodacaoException |
                 PagamentoException | ItemException ex) {
            JOptionPane.showMessageDialog(null, "Erro: " + ex.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(null, "Formato invalido, campos de número deve conter apenas números", "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void listHospedagens() {
        hospedagemTextArea.setText("");
        Set<String> hospedagens = hospedagemController.getHospedagens();
        for (String hospedagem : hospedagens) {
            hospedagemTextArea.append(hospedagem + "\n");
        }
    }

    private void searchHospedagem() {
        try {
            String id = searchIdField.getText();
            hospedagemDetailsArea.setText(hospedagemController.listarHospedagem(id).toString());
        } catch (HospedagemException | TipoAcomodacaoException ex) {
            hospedagemDetailsArea.setText("Erro: " + ex.getMessage());
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void addHospede() {
        try {
            String idHospedagem = txtHospedagemIdAddHospede.getText();
            String[] hospedeCpfs = txtHospedeAdd.getText().split(",");
            ArrayList<HospedeDto> hospedes = new ArrayList<>();
            for (String cpf : hospedeCpfs) {
                hospedes.add(hospedeController.getHospedeDto(cpf.trim()));
            }
            hospedagemController.addAcompanhante(idHospedagem, hospedes);
            JOptionPane.showMessageDialog(null, "Hospede(s) adicionado(s) com sucesso!");
        } catch (HospedeException | TipoAcomodacaoException | HospedagemException | AcomodacaoException ex) {
            JOptionPane.showMessageDialog(null, "Erro: " + ex.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void confirmAndCheckout() {
        try {
            String id = txtHospedagemIdCheckout.getText();
            HospedagemDto hospedagemDto = hospedagemController.getHospedagemDto(id);

            int confirm = JOptionPane.showConfirmDialog(null, "Confirma o checkout para a seguinte hospedagem?\n" + hospedagemDto.getId(), "Confirmar Checkout", JOptionPane.YES_NO_OPTION);
            if (confirm == JOptionPane.YES_OPTION) {
                PagamentoDto pagamento = null;
                if (!txtFinalPayment.getText().isEmpty()) {
                    double finalPayment = Double.parseDouble(txtFinalPayment.getText());
                    ETipoPagamento tipoPagamento = (ETipoPagamento) cbTipoPagamento.getSelectedItem();
                    pagamento = new PagamentoDto(tipoPagamento, new Date(), finalPayment);
                }
                hospedagemController.checkout(id, pagamento);
                acomodacaoController.alterarEstadoAcomodacao(hospedagemDto.getNumeroAcomodacao(), EEstadoOcupacao.DISPONIVEL);
                JOptionPane.showMessageDialog(null, "Checkout realizado com sucesso!");
            }
        } catch (HospedagemException | TipoAcomodacaoException | PagamentoException | AcomodacaoException |
                 HospedeException ex) {
            JOptionPane.showMessageDialog(null, "Erro: " + ex.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(null, "Formato invalido, campos de número deve conter apenas números", "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }
}